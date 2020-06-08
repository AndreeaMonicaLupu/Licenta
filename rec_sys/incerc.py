#%%
import pandas as pd
import numpy as np

#%%
#citesc din fisier id uri
likedPaintingsMatrix = pd.read_csv(r'C:\Users\Andreea\facultate\incercari\BD\picturi_apreciate.csv', sep=',',header=None)

picturi = pd.read_csv(r'C:\Users\Andreea\facultate\licenta\rec_sys\Picturi.csv', sep='#',
names=['id_pictura','cale','denumire','categorie','taguri','disponibil','pret','dimeniune','descriere'
])
print(picturi.id_pictura)

#%%
#ce citeste din csv ia ca pe matrice

id_likedPaintings = likedPaintingsMatrix.values[0]
print(id_likedPaintings)

#%%

def get_title_from_index(id_pictura):
   return picturi.denumire[id_pictura]

#%%
#iau pe rand fiecare id si iau titlu

for id_p in id_likedPaintings:
    #print(id_p)
    liked_painting=get_title_from_index(id_p)

    
    print(liked_painting)

#%%

#liked_painting=denumire_pictura


# %%
