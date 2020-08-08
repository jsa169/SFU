import sys
from pyspark.sql import SparkSession, functions, types, Row
import string, re

spark = SparkSession.builder.appName('reddit averages').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

wordbreak = r'[%s\s]+' % (re.escape(string.punctuation),)

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

def main(in_directory):
	file = spark.read.text(in_directory)

	split = file.select(functions.split(file['value'], wordbreak).alias('val')) 	#split string
	explode = split.select(functions.explode(split['val']))		#Explode into columns
	filtered = explode.filter(explode['col'] != "")		#filter out empty string
	lower = filtered.select(functions.lower(filtered['col']).alias('words')) 	#lower case
	group = lower.groupBy('words').agg(functions.count('words').alias('count'))		#group by words, and count
	result = group.sort(['count', 'words'], ascending = [False, True])		#sort results

	result.write.csv(out_directory, mode='overwrite')

if __name__=='__main__':
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]
    main(in_directory)