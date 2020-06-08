import { Component, OnInit } from '@angular/core';
import {  Router } from '@angular/router';
import { DataService } from 'src/shared/data.service';
import { GalerieService } from 'src/shared/categorie.service';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})
export class HomeComponent implements OnInit {
  id_loggedin :number;
  id_categorie: number;
  cale: string;

  pictura: Pictura[];
  
  
  constructor(private router: Router, private _dataservice:DataService, private _galerieservice: GalerieService, private service:Service) {
    this.service.getRecommendation().subscribe(res => {
      this.pictura = res;
    },
      err => {
        console.log(err);
      })
    
  }

  Redirect_Evenimente(cale, id_categorie){
    this.cale=cale;
    this.id_categorie = id_categorie;
    this._galerieservice.nextId(this.id_categorie);//trimit id_categorie
    console.log("id_cat", this.id_categorie);
    this.router.navigate([cale]);

    window.scrollTo(0, 0);
  }

  ngOnInit(): void {
    this._galerieservice.nextId(0);
    this._dataservice.sharedId.subscribe(id_loggedin => this.id_loggedin = id_loggedin)//ascult ce e in service de la login
    
  }

  Like(id_pictura: number){

    this.id_categorie =4;

    if(this.id_loggedin == 0){
      alert("Trebuie sa te conectezi pentru a aprecia pictuirle");
    }
     
    else{
      console.log('user cu id ', this.id_loggedin, 'liked pictura cu id ', id_pictura );

      this.service.postLikes(this.id_loggedin, id_pictura, this.id_categorie).subscribe();

    }
  }
}
