import { Component } from '@angular/core';

import { Interconectare } from './interconectare.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})

export class AppComponent {
  title = 'LupulCreativ';
  
  constructor(private ServiciuComunicare: Interconectare){

  }

  MetodaClick(numar: number) : void{

    this.ServiciuComunicare.metoda(numar);

  }


}
