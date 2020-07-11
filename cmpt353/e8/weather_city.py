import numpy as np
import pandas as pd
import sys

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.neighbors import KNeighborsClassifier

import warnings
warnings.simplefilter("ignore")

def main():

	#Data file names
	labelled_data = sys.argv[1]
	unlabelled_data = sys.argv[2]
	output = sys.argv[3]

	#Get training data
	train_from = pd.read_csv(labelled_data)
	X = train_from.iloc[:, 2:62]
	y = train_from.iloc[:,0]
	print (X)
	#Split train and valid
	X_train, X_valid, y_train, y_valid = train_test_split(X,y,test_size=0.3)

	#Get data to be used to predict
	X_predict = pd.read_csv(unlabelled_data).iloc[:, 2:62]

	#Create model
	model = make_pipeline(StandardScaler(), KNeighborsClassifier(n_neighbors=15))
	model.fit(X_train, y_train)

	#make prediction
	predictions = model.predict(X_predict)
	print('Model score:', model.score(X_valid, y_valid))

	#Save results to file
	pd.Series(predictions).to_csv(output, index=False, header=False)

if __name__ == '__main__':
    main()
