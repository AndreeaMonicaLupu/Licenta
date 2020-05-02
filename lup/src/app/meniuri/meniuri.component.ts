import { Component, OnInit } from '@angular/core';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';
import { DataService } from 'src/shared/data.service';

@Component({
  selector: 'app-meniuri',
  templateUrl: './meniuri.component.html',
  styleUrls: ['./meniuri.component.scss']
})
export class MeniuriComponent implements OnInit {

  pictura: Pictura[];
  categorie: number[];

  id_categorie: number;
  id_loggedin: number;

  constructor(private service:Service, private _dataservice:DataService) {
    this.service.getPictura('6').subscribe(res => {
      this.pictura = res;
    },
      err => {
        console.log(err);
      })

   }

  ngOnInit(): void {
    this._dataservice.sharedId.subscribe(id_loggedin => this.id_loggedin = id_loggedin)
   } 
   Like(id_pictura: number){
    this.id_categorie =6;

    if(this.id_loggedin == 0){
      alert("Trebuie sa te conectezi pentru a aprecia pictuirle");
    }
     
    else{
      console.log('user cu id ', this.id_loggedin, 'liked pictura cu id ', id_pictura, 'din categoria', 6  );

      this.service.postLikes(this.id_loggedin, id_pictura, this.id_categorie).subscribe();

    }
  }


}
