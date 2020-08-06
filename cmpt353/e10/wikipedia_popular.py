import sys
from pyspark.sql import SparkSession, functions, types

spark = SparkSession.builder.appName('reddit averages').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

wiki_schema = types.StructType([
    types.StructField('language', types.StringType()),
    types.StructField('page_name', types.StringType()),
    types.StructField('view_count', types.IntegerType()),
    types.StructField('return_size', types.IntegerType()),
])

def convertPath(a):
	b = a.split('/')[-1]
	b = b[11:]
	b = b.split('.')[0]
	b = b[:-4]
	return b

path_to_hour = functions.udf(convertPath, returnType=types.StringType())

def main(in_directory, out_directory):
	wiki_view = spark.read.csv(in_directory, sep=' ', schema=wiki_schema).withColumn('filename', functions.input_file_name())
	wiki_view = wiki_view.withColumn('hour',path_to_hour(wiki_view['filename']))

	wiki_view = wiki_view.filter(wiki_view['language'] == "en")
	wiki_view = wiki_view.filter(wiki_view['page_name'] != "Main_Page")
	wiki_view = wiki_view.filter(wiki_view['page_name'].startswith("Special:") == False).cache()

	group = wiki_view.groupBy('hour')
	max_view = group.agg(functions.max('view_count').alias('view_count'))


	result = max_view.join(wiki_view, on=['hour','view_count']).select('hour','page_name','view_count')
	result = result.sort('hour')
	result.write.csv(out_directory, mode='overwrite')


if __name__=='__main__':
	in_directory = sys.argv[1]
	out_directory = sys.argv[2]
	main(in_directory, out_directory)