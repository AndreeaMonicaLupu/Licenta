import { Component, AfterViewInit, DoCheck} from '@angular/core';
import { DataService } from 'src/shared/data.service';
import { ToastrService } from 'ngx-toastr';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})

export class AppComponent implements DoCheck {
  title = 'LupulCreativ';
  tip_login: string;
  id_loggedin:number;
  cale="/";

  constructor(private _dataservice:DataService, private toastr:ToastrService){

  }

  ngDoCheck() {
    
    this._dataservice.sharedId.subscribe(id_loggedin => 
    this.id_loggedin = id_loggedin);

    if(this.id_loggedin == 0)
    {
      this.tip_login = 'Login';
      this.cale="/login";
    }
    else
    {
      this.tip_login='Logout';
      this.cale = "";
    }
    
  }

  Logout(){
    
    if(this.tip_login=='Logout'){
      this._dataservice.nextId(0);
      this.toastr.warning('Te-ai deconectat', 'Pe data viitoare!');
    }
     
  }
}
