using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using WebAPI.Models;

namespace WebAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]

    public class ValuesController : ControllerBase
    {
        Service service = new Service();

        // GET api/values
        [HttpGet]
        [Route("{id_categorie}")] 
        public ActionResult<List<Pictura>> Get(string id_categorie)
        {
            return service.GetPictura(Convert.ToInt32(id_categorie));
        }
        [HttpGet]
        [Route("{username}/{parola}")] 
        public ActionResult<User> Get(string username, string parola)
        {
            return service.GetUser(username, parola);
        }

        [HttpGet]
        [Route("{username}/{parola}/{mail}")]
        public ActionResult<User> PostUser(string username, string parola, string mail)
        {
            if(mail == "null")
                return service.GetUser(username, parola);
            return service.PostUser(username, parola, mail);
        }

        [HttpPost]
        [Route("{id_user}/{id_pictura}/{id_categorie}")]
        public ActionResult<List<User>> PostLikes(int id_user, int id_pictura, int id_categorie)
        {
            return service.PostLikes(id_user, id_pictura, id_categorie);
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody] string value)
        {
        }

        // PUT api/values/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody] string value)
        {
        }

        // DELETE api/values/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}
