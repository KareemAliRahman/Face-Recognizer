import numpy as np
from sklearn.naive_bayes import GaussianNB
import time
from lbp import lbp

#Count method not implemented for numpy.dnarray type
def _count(array,value):
	return sum(map(lambda x:1 if(x==value) else 0,array))

def precision(results,trueresults):
	return sum(map((lambda x,y:1 if(x==y==1) else 0),results,trueresults))/float(len(results))


def recall(results,trueresults):
	return sum(map((lambda x,y:1 if(x==y==1) else 0),results,trueresults))/float(count(trueresults,1))

def f1(results,trueresults):
	return precision(results,trueresults)*recall(results,trueresults)/(precision(results,trueresults)+recall(results,trueresults))


count=_count


def mainMethod():
	gnb=GaussianNB()
	train=[]
	trainresults=[]
	testdata=[]
	testresults=[]
	f=lambda x: map(int,x)

	###Training data###

	training=open('train.txt','r')
	trainingfiles=training.read().splitlines()
	training.close()
 	for x in trainingfiles:
		train+=[lbp(x.split(',')[0])]
		trainresults+=x.split(',')[1].split('\r')[0].split('\n')[0]
	trainresults=f(trainresults)
 	test=open('test.txt','r')
 	testfiles=test.read().splitlines()
 	test.close()

 	###Test data###

	for x in testfiles:
		testdata+=[lbp(x.split(',')[0])]
		testresults+=x.split(',')[1].split('\r')[0].split('\n')[0]

	testresults=f(testresults)
	train=np.array(train, dtype=np.uint)
	testdata=np.array(testdata,dtype=np.uint)
	trainresults=np.array(trainresults)
	testresults=np.array(testresults)
  	gnb.fit(train,trainresults)
	predictions=gnb.predict(testdata)


	print "Took: %.3f s \nPrecision: %.2f \nRecall: %.2f \nF1 Measure: %.2f" %(
	 	time.time()-currenttime,
	 	precision(predictions,testresults),
	 	recall(predictions,testresults),
	 	f1(predictions,testresults))



if __name__=="__main__":
	currenttime=time.time()
	mainMethod()