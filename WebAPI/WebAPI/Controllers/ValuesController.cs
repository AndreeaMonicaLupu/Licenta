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

        // GET api/values/5
        // [HttpGet("{id}")]
        // public ActionResult<string> Get(int id)
        //{
        // return "value";
        // }

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
