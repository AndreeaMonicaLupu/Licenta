import { Component, OnInit } from '@angular/core';
import {Picturi} from '../picturi';

@Component({
  selector: 'app-felicitari',
  templateUrl: './felicitari.component.html',
  styleUrls: ['./felicitari.component.scss']
})
export class FelicitariComponent implements OnInit {

  lista_picturi = pictura;

  constructor() { }

  ngOnInit(): void {
  }

}

export const pictura : Picturi[] =[
  { id: 1, name: 'Felicitari' },
  { id: 2, name: 'Felicitari' },
  { id: 3, name: 'Felicitari' }
];
