using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebAPI.Models
{
    public class User
    {
        public int id_user { get; set; }
        public string username { get; set; }
        public string mail { get; set; }
        public string parola { get; set; }
        public string picturi_apreciate { get; set; }

        public User()
        {
            this.id_user = id_user;
            this.username = username;
            this.mail = mail;
            this.parola = parola;
            this.picturi_apreciate = picturi_apreciate;
        }

        //add function?
    }
}
