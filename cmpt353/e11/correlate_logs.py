import sys
from pyspark.sql import SparkSession, functions, types, Row
import re
from math import sqrt
spark = SparkSession.builder.appName('correlate logs').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

line_re = re.compile(r"^(\S+) - - \[\S+ [+-]\d+\] \"[A-Z]+ \S+ HTTP/\d\.\d\" \d+ (\d+)$")


def line_to_row(line):
    """
    Take a logfile line and return a Row object with hostname and bytes transferred. Return None if regex doesn't match.
    """
    m = line_re.match(line)
    if m:
        # TODO
        row = Row(hostname=m.group(1), B_transfered=m.group(2))
        return row
    else:
        return None


def not_none(row):
    """
    Is this None? Hint: .filter() with it.
    """
    return row is not None


def create_row_rdd(in_directory):
    log_lines = spark.sparkContext.textFile(in_directory)
    # TODO: return an RDD of Row() objects
    log_rows = log_lines.map(line_to_row)
    log_rows = log_rows.filter(not_none)
    return log_rows


def main(in_directory):
    logs = spark.createDataFrame(create_row_rdd(in_directory))
    log = logs.groupBy('hostname')

    number_of_request = log.agg(functions.count('hostname').alias('xi'))
    sum_transferred = log.agg(functions.sum('B_transfered').alias('yi'))

    data_point = number_of_request.join(sum_transferred, on=['hostname'])

    data_point = data_point.withColumn('xi^2', data_point['xi']**2)
    data_point = data_point.withColumn('yi^2', data_point['yi']**2)
    data_point = data_point.withColumn('xiyi', data_point['yi']*data_point['xi'])
    data_point = data_point.withColumn('1', functions.lit(1))   #functiuons.lit() from https://stackoverflow.com/questions/32788322/how-to-add-a-constant-column-in-a-spark-dataframe 

    sums = data_point.groupBy().agg(
    		functions.sum(data_point['xi']).alias('xi'),
    		functions.sum(data_point['yi']).alias('yi'),
    		functions.sum(data_point['xi^2']).alias('xi^2'),
    		functions.sum(data_point['yi^2']).alias('yi^2'),
    		functions.sum(data_point['xiyi']).alias('xiyi'),
    		functions.sum(data_point['1']).alias('n')
    	)
    
    sum_xi, sum_yi, sum_xi2, sum_yi2, sum_xiyi, n = sums.first()

    numerator = n*sum_xiyi - sum_xi*sum_yi
    denominator = sqrt((n*sum_xi2-sum_xi**2) * (n*sum_yi2-sum_yi**2))
    r = numerator/denominator

    # TODO: calculate r.

    print("r = %g\nr^2 = %g" % (r, r**2))


if __name__=='__main__':
    in_directory = sys.argv[1]
    main(in_directory)
