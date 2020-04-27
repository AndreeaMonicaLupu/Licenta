using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebAPI.Models;

namespace WebAPI
{
    public class ReadCsv
    {
        string path = "C:\\Users\\Andreea\\facultate\\licenta\\lup\\BD\\Picturi.csv"; //picturi.csv
       
        public List<Pictura> Read()
        {
            List<Pictura> pictura = new List<Pictura>();
            string[] lines = System.IO.File.ReadAllLines(path);

            for (int i = 1; i < lines.Length; i++) //linii; sare peste capul tabelului
            {
                string[] fields = lines[i].Split("##".ToCharArray()); 
                
                pictura.Add(new Pictura
                {
                    id_pictura = Int32.Parse(fields[0]),
                    cale_poza = fields[1],
                    denumire = fields[2],
                    categorie = Int32.Parse(fields[3]),
                    taguri = fields[4],
                    disponibilitate = Int32.Parse(fields[5]),
                    pret = Int32.Parse(fields[6]),
                    dimensiune = fields[7],
                    descriere = fields[8]

                });

            }
            return pictura;

        }
    }
}
