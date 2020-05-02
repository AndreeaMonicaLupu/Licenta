import { Component, OnInit, Output, EventEmitter } from '@angular/core';
import { User } from 'src/shared/user';
import { Service } from 'src/shared/service';
import { ToastrService } from 'ngx-toastr';
import { DataService } from 'src/shared/data.service';
import {  Router } from '@angular/router';
import {FormControl, Validators} from '@angular/forms';
import { GalerieService } from 'src/shared/categorie.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})

export class LoginComponent implements OnInit {
  user: User;
  id_loggedin :number;
  cale: string;
  email = new FormControl('', [Validators.required, Validators.email]);

  @Output() messageEvent = new EventEmitter<number>();

  constructor(private router: Router, private service:Service, private toastr:ToastrService, private _dataservice: DataService, private _galerieservice: GalerieService ) { 
    
  }

  ngOnInit(): void {
    this._dataservice.sharedId.subscribe(id_loggedin => this.id_loggedin = id_loggedin);//ca sa ascult service
    this._galerieservice.nextId(0);
  }

  Login(username: string, password: string, mail:string){ 

    console.log("login:-----", username,"----", password,"----", mail);
    
    if(username == "" || password =="" ||mail==""){
      alert("Atentie!\n Completeaza toate campurile inainte de a te inregistra!");
    }
    
    else{
      this.service.getUser( username, password, mail ).subscribe(res => {
        this.user = res;
  
        //iau id
        this.id_loggedin = this.user.id_user;
        this.messageEvent.emit(this.id_loggedin);
        this._dataservice.nextId(this.id_loggedin);//ca sa trimit nou id
  
        if(this.user.username == null){
          this.toastr.error('Username, paarola gresita, sau nu exista cont');
        }
      else{
        this.toastr.success(this.user.username,'Bine ai venit,');
        this.Redirect_Evenimente('');
      }
       
        
      },
        err => {
          console.log(err);
        })
    }
    
  }
  
  Redirect_Evenimente(cale){
    this.cale=cale;

    this.router.navigate([cale]);

    window.scrollTo(0, 0);
  }

}
