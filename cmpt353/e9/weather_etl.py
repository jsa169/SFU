import sys
from pyspark.sql import SparkSession, functions, types
from pyspark.sql import Row


spark = SparkSession.builder.appName('weather ETL').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.4' # make sure we have Spark 2.4+

observation_schema = types.StructType([
    types.StructField('station', types.StringType()),
    types.StructField('date', types.StringType()),
    types.StructField('observation', types.StringType()),
    types.StructField('value', types.IntegerType()),
    types.StructField('mflag', types.StringType()),
    types.StructField('qflag', types.StringType()),
    types.StructField('sflag', types.StringType()),
    types.StructField('obstime', types.StringType()),
])


def main(in_directory, out_directory):

    weather = spark.read.csv(in_directory, schema=observation_schema)

    # TODO: finish here.

    #Filters
    filtered = weather.filter(weather.qflag.isNull()) #field qflag (quality flag) is null
    filtered = filtered.filter(weather.station.startswith('CA')) #the station starts with 'CA'
    filtered = filtered.filter(weather.observation == 'TMAX')#the observation is 'TMAX'

    #Selections
    cleaned_data = filtered.select(
    	filtered.station,
    	filtered.date,
    	(filtered.value/10).alias('TMAX')
    )
    #Save to file
    cleaned_data.write.json(out_directory, compression='gzip', mode='overwrite')


if __name__=='__main__':
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]
    main(in_directory, out_directory)
