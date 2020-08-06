import sys
from pyspark.sql import SparkSession, functions, types

spark = SparkSession.builder.appName('reddit relative scores').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

comments_schema = types.StructType([
    types.StructField('archived', types.BooleanType()),
    types.StructField('author', types.StringType()),
    types.StructField('author_flair_css_class', types.StringType()),
    types.StructField('author_flair_text', types.StringType()),
    types.StructField('body', types.StringType()),
    types.StructField('controversiality', types.LongType()),
    types.StructField('created_utc', types.StringType()),
    types.StructField('distinguished', types.StringType()),
    types.StructField('downs', types.LongType()),
    types.StructField('edited', types.StringType()),
    types.StructField('gilded', types.LongType()),
    types.StructField('id', types.StringType()),
    types.StructField('link_id', types.StringType()),
    types.StructField('name', types.StringType()),
    types.StructField('parent_id', types.StringType()),
    types.StructField('retrieved_on', types.LongType()),
    types.StructField('score', types.LongType()),
    types.StructField('score_hidden', types.BooleanType()),
    types.StructField('subreddit', types.StringType()),
    types.StructField('subreddit_id', types.StringType()),
    types.StructField('ups', types.LongType()),
    #types.StructField('year', types.IntegerType()),
    #types.StructField('month', types.IntegerType()),
])


def main(in_directory, out_directory):
    comments = spark.read.json(in_directory, schema=comments_schema)

    # TODO

    comments = comments.select('score','author','subreddit').cache()
    averages = comments.groupBy('subreddit')
    result = averages.agg(functions.avg('score'))
    averages_by_score = result.sort('avg(score)', ascending=False)

    averages_by_score = averages_by_score.filter(averages_by_score['avg(score)'] != 0)
    averages_by_score=functions.broadcast(averages_by_score)
    joined = averages_by_score.join(comments, on=['subreddit'])

    joined = joined.select(
    		joined['subreddit'],
    		joined['author'],
    		(joined['score']/joined['avg(score)']).alias('rel_score')
    	).cache()

    grouped = joined.groupBy('subreddit')
    result = grouped.agg(functions.max('rel_score').alias('rel_score'))
    result = functions.broadcast(result)

    best_author = result.join(joined, on=['rel_score','subreddit']).select('subreddit', 'author','rel_score')

    best_author.show();

    best_author.write.json(out_directory, mode='overwrite')



if __name__=='__main__':
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]
    main(in_directory, out_directory)
