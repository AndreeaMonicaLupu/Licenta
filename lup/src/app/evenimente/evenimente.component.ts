import { Component, OnInit } from '@angular/core';
import { DataService } from 'src/shared/data.service';
import { GalerieService } from 'src/shared/categorie.service';

@Component({
  selector: 'app-evenimente',
  templateUrl: './evenimente.component.html',
  styleUrls: ['./evenimente.component.scss']
})
export class EvenimenteComponent implements OnInit {

  id_loggedin: number;
  
  constructor(private _dataservice:DataService, private _galerieservice: GalerieService) { }

  ngOnInit(): void {
    this._dataservice.sharedId.subscribe(id_loggedin => this.id_loggedin = id_loggedin);
    this._galerieservice.nextId(0);
  }

}
