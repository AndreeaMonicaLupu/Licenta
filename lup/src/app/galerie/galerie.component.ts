import { Component, OnInit } from '@angular/core';

import { Interconectare } from '../interconectare.service';
import { Subscription } from 'rxjs';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';

@Component({
  selector: 'app-galerie',
  templateUrl: './galerie.component.html',
  styleUrls: ['./galerie.component.scss']
})
export class GalerieComponent implements OnInit {

  nr_categorie: number=0;
  Subscription_nr_cat: Subscription;
  galerie="categorii";
  title = 'Galerie';

  constructor( private ServiciuComunicare: Interconectare ) { }
    

  ngOnInit(): void {
    this.InitializeSubscription();

  }
  
  InitializeSubscription(): number{

    this.Subscription_nr_cat=this.ServiciuComunicare.nr_cat$.subscribe((valoare: number)=>
    {  
      this.nr_categorie = valoare;
      console.log(this.nr_categorie); 
      
    }); 
    return this.nr_categorie;
  }

  Metoda(): number{
    return this.nr_categorie;
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
      default: this.title =""; break;
    }
  }
}
