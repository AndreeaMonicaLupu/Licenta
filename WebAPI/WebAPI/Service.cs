using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebAPI.Models;

namespace WebAPI
{
    public class Service
    {
        ReadCsv reader = new ReadCsv();

        public List<Pictura>  GetPictura(int id_categorie)//param -> categorie
        {
            return reader.Read().Where(a => a.categorie == id_categorie).ToList(); ;
        }

        public List<Pictura> getRecommendation()//param -> categorie
        {
            return reader.Recommendation();
        }

        public User GetUser(string username, string parola)
        {
            return reader.ReadUsear(username, parola);
        }
        public User PostUser(string username, string parola, string mail)
        {
            return reader.PostUser(username, parola, mail);
        }

        public List<User> PostLikes(int id_user, int id_pictura, int id_categorie)
        {
            return reader.PostLikes(id_user, id_pictura, id_categorie);
        }

    }
}
