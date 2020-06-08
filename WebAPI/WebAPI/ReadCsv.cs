using System;
using System.Collections.Generic;
using System.Diagnostics;
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

            int id_user = lines.Length + 1;
            bool exista_inregistrare = user_existent(username);

            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@path, true))
            {

                if(exista_inregistrare == false)
                {

                    user.id_user = id_user;
                    user.username = username;
                    user.mail = mail;
                    user.parola = parola;
                    user.picturi_apreciate = "0";

                    file.WriteLine(user.id_user + "#" + user.username + "#" + user.mail
                        + "#" + user.parola + "#" + user.picturi_apreciate);
                }
                
            }

            scriere_picturi_apreciate(path, id_user);
            run_python();

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

                user.Add(new User
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

            scriere_picturi_apreciate(path, id_user);
            run_python();

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

                if (username == fields[1] && parola == fields[3])
                {
                    user_cautat.id_user = Int32.Parse(fields[0]);
                    user_cautat.username = fields[1];
                    user_cautat.mail = fields[2];
                    user_cautat.parola = parola;
                    user_cautat.picturi_apreciate = fields[4];

                    //aici scriu in fisier! picturi apreciate
                    scriere_picturi_apreciate(path, user_cautat.id_user);
                    run_python();

                    return user_cautat;
                }

            }
            return user_negasit;

        }

        public bool user_existent(string username)
        {

            string path = "C:\\Users\\Andreea\\facultate\\licenta\\lup\\BD\\user.csv";
            string[] lines = System.IO.File.ReadAllLines(path);

            for (int i = 0; i < lines.Length; i++)
            {
                string[] fields = lines[i].Split("#".ToCharArray());

                if (username == fields[1])
                {
                    return true;
                }

            }

            return false;
        }

        public List<Pictura> Read()
        {
            string path = "C:\\Users\\Andreea\\facultate\\licenta\\lup\\BD\\Picturi.csv";

            List<Pictura> pictura = new List<Pictura>();

            string[] lines = System.IO.File.ReadAllLines(path);

            for (int i = 1; i < lines.Length; i++) //linii; sare peste capul tabelului
            {
                string[] fields = lines[i].Split('#') ;

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

        public void scriere_picturi_apreciate(string path, int id)
        {
            string[] lines = System.IO.File.ReadAllLines(path);
            string write_path = "C:\\Users\\Andreea\\facultate\\licenta\\sistem_recomandari\\picturi_apreciate.csv";
            string[] idPicturi;

            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@write_path, false))
            {
                for (int i = 0; i < lines.Length; i++)
                {
                    string[] element = lines[i].Split('#');

                    if (Int32.Parse(element[0]) == id)
                    {
                        string[] idPicturi_categorie = element[4].Split(','); //iau pic apreciate

                        for (int j = 0; j < idPicturi_categorie.Length; j++)
                        {
                            idPicturi = idPicturi_categorie[j].Split('/');

                            if (idPicturi[0] != "0")
                            {
                                if (j < idPicturi_categorie.Length - 1) //-1 ca sa nu am ultim caracter ","
                                {
                                    file.Write(idPicturi[0] + ',');
                                }
                                else
                                {
                                    file.Write(idPicturi[0]);
                                }
                            }
                            else
                            if(idPicturi[0]=="0" && element[4].Length==1)
                            {
                                file.Write("13");
                            }

                        }

                    }
                }

            }
        }

        public void run_python()
        {
            Process cmd = new Process();
            cmd.StartInfo.FileName = "cmd.exe";
            cmd.StartInfo.RedirectStandardInput = true;
            cmd.StartInfo.RedirectStandardOutput = true;
            cmd.StartInfo.CreateNoWindow = true;
            cmd.StartInfo.UseShellExecute = false;
            cmd.Start();

            cmd.StandardInput.WriteLine("conda activate tensorflow");

            cmd.StandardInput.WriteLine("C:\\Users\\Andreea\\Miniconda3\\envs\\tensorflow\\python C:\\Users\\Andreea\\facultate\\licenta\\rec_sys\\RECOMANDARI.py");
            cmd.StandardInput.Flush();
            cmd.StandardInput.Close();
            cmd.WaitForExit();
            Console.WriteLine(cmd.StandardOutput.ReadToEnd());
        }

        public void citire_recomandari()//Pictura pictura
        {
            string picturi_recomandate = null;
            string recomandare_finala = "";

            string path = "C:\\Users\\Andreea\\facultate\\licenta\\sistem_recomandari\\lista_picturi_recomandate.txt";

            string[] lines = System.IO.File.ReadAllLines(path);
            for (int i = 0; i < lines.Length; i++)
            {
                lines[i] = lines[i].Replace('[', ' ');
                lines[i] = lines[i].Replace(']', ' ');

                string[] tuplu = lines[i].Split(',');
                int id1 = Int32.Parse(tuplu[0].Replace('(', ' '));
                int id2 = Int32.Parse(tuplu[2].Replace('(', ' '));

                picturi_recomandate += id1.ToString() + ',' + id2.ToString() + ',';

            }

            picturi_recomandate = picturi_recomandate.Remove(picturi_recomandate.Length - 1); //ultim caracter ','
            //Console.WriteLine(picturi_recomandate);

            string[] picturi_recomandate_fara_dubluri = elimina_dubluri(picturi_recomandate);
            picturi_recomandate = "";

            for (int i = 0; i < picturi_recomandate_fara_dubluri.Length; i++)
            {
                picturi_recomandate += picturi_recomandate_fara_dubluri[i] + ',';
            }
            picturi_recomandate = picturi_recomandate.Remove(picturi_recomandate.Length - 1);

            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\\Users\\Andreea\\facultate\\licenta\\sistem_recomandari\\picturi_recomandate.txt", false))
            {
                file.WriteLine(picturi_recomandate);
            }
        }

        public string[] elimina_dubluri(string strr)
        {
            string[] s = strr.Split(',');
            string[] q = s.Distinct().ToArray();
            return q;
        }

        public List<Pictura> Recommendation()
        {
            //citit recomandarile
            //facut list obiecte tip pictura pe care le returnez

            List<Pictura> pictura = new List<Pictura>();

            List<Pictura> picturi_recomandate = new List<Pictura>();

            pictura = Read();

            citire_recomandari();

            string[] lista_picturi = System.IO.File.ReadAllLines("C:\\Users\\Andreea\\facultate\\licenta\\sistem_recomandari\\picturi_recomandate.txt");

            for (int i = 0; i < lista_picturi.Length; i++)
            {
                string[] id_pictura = lista_picturi[i].Split(',');

                for (int j = 0; j < id_pictura.Length; j++)
                {
                    foreach (var p in pictura)
                    {
                        if (Int32.Parse(id_pictura[j]) == p.id_pictura)
                        {
                            picturi_recomandate.Add(new Pictura
                            {
                                id_pictura = p.id_pictura,
                                cale_poza = p.cale_poza,
                                denumire = p.denumire,
                                categorie = p.categorie,
                                taguri = p.taguri,
                                disponibilitate = p.disponibilitate,
                                pret = p.pret,
                                dimensiune = p.dimensiune,
                                descriere = p.descriere

                            });
                        }
                    }
                }

            }
            return picturi_recomandate;
        }
    }
}
