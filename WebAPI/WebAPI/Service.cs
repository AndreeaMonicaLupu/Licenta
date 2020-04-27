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
    }
}
