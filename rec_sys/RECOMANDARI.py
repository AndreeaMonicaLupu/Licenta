#%%
import pandas as pd
import numpy as np
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# %%
#functii pentru idex->titlu si invers

def get_title_from_index(id_pictura):
	return picturi.denumire[id_pictura]
#%%
def get_index_from_title(denumire):
	return df.index[df['denumire']==denumire].tolist()[0]

# %%
#citire din csv si split
df = pd.read_csv(r'C:\Users\Andreea\facultate\licenta\lup\BD\Picturi.csv', sep='#',
names=['id_pictura','cale','denumire','categorie','taguri','disponibil','pret','dimeniune','descriere'
])
#df.columns

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
#print ("Combined Features:", df["combined_features"].head() )

# %%
#creez count matrix pornind de la coloana noua
cv = CountVectorizer()

count_matrix = cv.fit_transform(df["combined_features"])

#print(count_matrix)
#%%
#calculez similritate (cu cosine_similarity) bazata pe matricea de mai sus
cosine_sim = cosine_similarity(count_matrix) 


# %%
#citesc din fisier id uri
likedPaintingsMatrix = pd.read_csv(r'C:\Users\Andreea\facultate\licenta\sistem_recomandari\picturi_apreciate.csv', sep=',',header=None)

picturi = pd.read_csv(r'C:\Users\Andreea\facultate\licenta\lup\BD\Picturi.csv', sep='#',
names=['id_pictura','cale','denumire','categorie','taguri','disponibil','pret','dimeniune','descriere'
])
#print(picturi.id_pictura)

# %%
#ce citeste din csv ia ca pe matrice

id_likedPaintings = likedPaintingsMatrix.values[0]
#print(id_likedPaintings)

# %%
similar_paintings_list=[]

for id_p in id_likedPaintings:
    #print(id_p)
    liked_painting=get_title_from_index(id_p)
    #print(cosine_sim)
    
    #iau id-ul picturii apreciate
    painting_index = get_index_from_title(liked_painting)
    similar_painting =  list(enumerate(cosine_sim[painting_index]))
    #print(similar_painting)

    #lista picturilor asemantoare, sortata
    sorted_similar_paintings = sorted(similar_painting,key=lambda x:x[1],reverse=True)
    similar_paintings_list.append(sorted_similar_paintings[1:3])
    

    # afisez primele 2
    #print('pentru', liked_painting, ': ', sorted_similar_paintings[1:3])
   # print(liked_painting)
print(similar_paintings_list)

# %%

with open(r'C:\Users\Andreea\facultate\licenta\sistem_recomandari\lista_picturi_recomandate.txt', 'w') as f:
    for item in similar_paintings_list:
        f.write("%s\n" % item)

print('recommendation has been made...')
# %%

# %%
