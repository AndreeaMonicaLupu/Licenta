using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using WebAPI.Models;

namespace WebAPI
{
    public class ReadCsv
    {
        public User PostUser(string username, string parola, string mail)
        {
            string path = "C:\\Users\\Andreea\\facultate\\licenta\\lup\\BD\\user.csv";
         
            User user = new User();

            string[] lines = System.IO.File.ReadAllLines(@path);

            int id_user =lines.Length+1;

            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@path, true))
            {
                user.id_user = id_user;
                user.username = username;
                user.mail = mail;
                user.parola = parola;
                user.picturi_apreciate = "0";

                file.WriteLine(user.id_user + "#" + user.username + "#" + user.mail
                    + "#" + user.parola + "#" + user.picturi_apreciate);
            }
            


            return user;
        }

        public List<User> PostLikes(int id_user, int id_pictura, int id_categorie)
        {
            string path = "C:\\Users\\Andreea\\facultate\\licenta\\lup\\BD\\user.csv";

            List<User> user = new List<User>();

            string[] lines = System.IO.File.ReadAllLines(path);

            for (int i = 0; i < lines.Length; i++) 
            {
                string[] fields = lines[i].Split('#');

                user.Add( new User
                {
                    id_user = Int32.Parse(fields[0]),
                    username = fields[1],
                    mail = fields[2],
                    parola = fields[3],
                    picturi_apreciate = fields[4]
                });

            }

            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@path, false))
           
            {
                foreach (var u in user)
                {
                    if (u.id_user == id_user)
                    {
                        u.picturi_apreciate += "," + id_pictura + "/" + id_categorie;
                    }
                    
                    file.WriteLine(u.id_user + "#" + u.username + "#" + u.mail + "#"
                        + u.parola + "#" + u.picturi_apreciate);
                    
                }
            }

            return user;
        }


        public User ReadUsear(string username, string parola)
        {
            User user_cautat = new User();
            User user_negasit = new User();

            string path = "C:\\Users\\Andreea\\facultate\\licenta\\lup\\BD\\user.csv";
            string[] lines = System.IO.File.ReadAllLines(path);

            for (int i = 0; i < lines.Length; i++) 
            {
                string[] fields = lines[i].Split("#".ToCharArray());

                if(username == fields[1] &&parola == fields[3])
                {
                    user_cautat.id_user = Int32.Parse(fields[0]);
                    user_cautat.username = fields[1];
                    user_cautat.mail = fields[2];
                    user_cautat.parola = parola;
                    user_cautat.picturi_apreciate = fields[4];

                    return user_cautat;
                }

            }
            return user_negasit;

        }
        public List<Pictura> Read()
        {
            string path = "C:\\Users\\Andreea\\facultate\\licenta\\lup\\BD\\Picturi.csv";

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
