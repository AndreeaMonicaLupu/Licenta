import { Component, OnInit } from '@angular/core';

import { Subscription } from 'rxjs';
import { DataService } from 'src/shared/data.service';
import { GalerieService } from 'src/shared/categorie.service';

@Component({
  selector: 'app-galerie',
  templateUrl: './galerie.component.html',
  styleUrls: ['./galerie.component.scss']
})
export class GalerieComponent implements OnInit {

  nr_categorie: number=0;
  id_loggedin: number;
  galerie="categorii";
  title :string;
  comentariu=" ";

  constructor( private _dataservice:DataService, private _galerieservice: GalerieService ) {
    this._galerieservice.sharedCategorieId.subscribe(id_categorie => this.nr_categorie = id_categorie);
    this.Alege_Categorie(this.nr_categorie);
   }
    

  ngOnInit(): void {
    this._dataservice.sharedId.subscribe(id_loggedin => this.id_loggedin = id_loggedin);
  }


  Alege_Categorie(nr_categorie){
    
    this.nr_categorie = nr_categorie;
    
    switch(this.nr_categorie){
      case 1 : this.title ="Picturi pe panza"; break;
      case 2 : this.title ="Picturi pe perete";break;
      case 3 : this.title ="Picturi pe cani/ pahare";break;
      case 4 : this.title ="Felicitari";break;
      case 5 : this.title ="Martisoare"; break;
      case 6 : this.title ="Meniuri"; break;
      default: this.title ="Galerie"; break;
    }
    
  }

  adaugareComenatriu(comentariu: string ){
    this.comentariu = comentariu;
    alert(this.comentariu);
  }

}
