using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebAPI.Models
{
    public class Pictura
    {
       
        public int id_pictura { get; set; }
        public string cale_poza { get; set; }
        public string denumire { get; set; }
        public int categorie { get; set; }
        public string taguri { get; set; }
        public int disponibilitate { get; set; }
        public int pret { get; set; }
        public string dimensiune { get; set; }
        public string descriere { get; set; }

        public Pictura()
        {
            this.id_pictura = id_pictura;
            this.cale_poza = cale_poza;
            this.denumire = denumire;
            this.categorie = categorie;
            this.taguri = taguri;
            this.pret = pret;
            this.dimensiune = dimensiune;
            this.descriere = descriere;

        }

    }
}
