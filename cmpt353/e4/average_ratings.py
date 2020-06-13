
import numpy as np
import pandas as pd
import difflib as dl
import sys

movie_list = open(sys.argv[1]).readlines()
movie_list = pd.DataFrame(movie_list, columns=['title'])
movie_list = movie_list.replace(r'\n',' ', regex=True) #https://stackoverflow.com/questions/44227748/removing-newlines-from-messy-strings-in-pandas-dataframe-cells
movie_rating = pd.read_csv(sys.argv[2])

movie_rating['title'] = movie_rating['title'].apply(dl.get_close_matches, n=1, possibilities=movie_list['title']) #search movie
movie_rating = movie_rating[movie_rating['title'].apply(len) != 0] #remove ones without a match
movie_rating['title'] = movie_rating['title'].apply(''.join) #https://stackoverflow.com/questions/37347725/converting-a-panda-df-list-into-a-string/37347844
movie_rating=movie_rating.groupby('title',as_index=False).mean().round(2) #group by title and average the rating

movie_rating.to_csv(sys.argv[3])