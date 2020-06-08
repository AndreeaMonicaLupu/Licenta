#%%
import pandas as pd
import numpy as np
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# %%
#functii pentru idex->titlu si invers

def get_title_from_index(id_pictura):
	return df[df.id_pictura == id_pictura]['denumire']
#%%
def get_index_from_title(denumire):
	return df.index[df['denumire']==denumire].tolist()[0]

#%%
#citire din csv si split

df = pd.read_csv(r'C:\Users\Andreea\facultate\licenta\rec_sys\Picturi.csv', sep='#',
names=['id_pictura','cale','denumire','categorie','taguri','disponibil','pret','dimeniune','descriere'
])
df.columns
# %%
#dupa ce caracteristici vreau sa faca recomandarile

features = ['categorie','taguri']

# %%
#creez o coloana, care combina caracteristicile
for feature in features:
	df[feature] = df[feature].fillna('')
	
def combine_features(row):
	try:
		return row['taguri'] +" "+row['categorie']
	except:
		print ("Error:", row)	

df["combined_features"] = df.apply(combine_features,axis=1)


# %%
print ("Combined Features:", df["combined_features"].head() )

# %%
#creez count matrix pornind de la coloana noua
cv = CountVectorizer()

count_matrix = cv.fit_transform(df["combined_features"])

print(count_matrix)

# %%
#calculez similritate (cu cosine_similarity) bazata pe matricea de mai sus
cosine_sim = cosine_similarity(count_matrix) 

#%%
#citesc din fisier id uri
id_likedPaintings = pd.read_csv(r'C:\Users\Andreea\facultate\incercari\BD\picturi_apreciate.csv', sep=' ')
print(id_likedPaintings)
#iau pe rand fiecare id

#de la id -> denumire

#liked_painting=denumire_pictura


#%%

#user alege o pictura
liked_painting = "Lupul Alfa"
#%%

print(cosine_sim)
# %%
#iau id-ul picturii apreciate

#!nu merge functia. problema la id_pictura
painting_index = get_index_from_title(liked_painting)
similar_painting =  list(enumerate(cosine_sim[painting_index]))

#"Lupul Alfa" are id-ul 2. am dat id-ul asa, ca sa vad daca merge restul programului

#similar_paintings =  list(enumerate(cosine_sim["Lupul Alfa"]))
print(similar_painting)

# %%
#lista picturilor asemantoare, sortata

sorted_similar_paintings = sorted(similar_painting,key=lambda x:x[1],reverse=True)
print(similar_painting)
#%%
# afisez primele 5

sorted_similar_paintings[1:3]

# %%
