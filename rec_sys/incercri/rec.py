#%%
import pandas as pd
import numpy as np
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity


# %%
def get_title_from_index(index):
	return df[df.index == index]['title'].values[0]

def get_index_from_title(title):
	return df[df.title == title]['index'].values[0]

# %%
##Step 1: Read CSV File
df = pd.read_csv(r'C:\Users\Andreea\facultate\licenta\rec_sys\movie_dataset.csv', sep=',',
names=['index','budget','genres','homepage','id','keywords','original_language','original_title','overview','popularity','production_companies','production_countries','release_date','revenue','runtime','spoken_languages','status','tagline','title','vote_average','vote_count','cast','crew','director'
])
print (df.head)

# %%
##Step 2: Select Features

features = ['keywords','cast','genres','director']

# %%
##Step 3: Create a column in DF which combines all selected features
for feature in features:
	df[feature] = df[feature].fillna('')

def combine_features(row):
	try:
		return row['keywords'] +" "+row['cast']+" "+row["genres"]+" "+row["director"]
	except:
		print ("Error:", row)	

df["combined_features"] = df.apply(combine_features,axis=1)

print ("Combined Features:", df["combined_features"].head() )

# %%
##Step 4: Create count matrix from this new combined column
cv = CountVectorizer()

count_matrix = cv.fit_transform(df["combined_features"])

print(count_matrix)

# %%
##Step 5: Compute the Cosine Similarity based on the count_matrix
cosine_sim = cosine_similarity(count_matrix) 
movie_user_likes = "Avatar"

# %%
## Step 6: Get index of this movie from its title
movie_index = get_index_from_title(movie_user_likes)

similar_movies =  list(enumerate(cosine_sim[movie_index]))
print(similar_movies)

# %%
## Step 7: Get a list of similar movies in descending order of similarity score
sorted_similar_movies = sorted(similar_movies,key=lambda x:x[1],reverse=True)
print(sorted_similar_movies)
#%%
## Step 8: Print titles of first 50 movies
i=0
for element in sorted_similar_movies:
		print (get_title_from_index(element[0]))
		i=i+1
		if i>5:
			break

# %%
