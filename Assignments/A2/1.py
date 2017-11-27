from pyspark import SparkContext, SparkConf
import time


conf = SparkConf().setAppName('pubmed_open_access').setMaster('local[32]')
sc = SparkContext(conf=conf)

if __name__ == "__main__":
    text_file = sc.textFile("1.txt")
    counts = text_file.flatMap(lambda line: line.split(" ")).map(lambda word: (word, 1)).reduceByKey(lambda a, b: a + b)
    print(counts)
    time.sleep(30)
    counts.saveAsTextFile("2.txt")
