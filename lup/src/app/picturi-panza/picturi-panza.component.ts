import { Component, OnInit } from '@angular/core';
import {Picturi} from '../picturi';

@Component({
  selector: 'app-picturi-panza',
  templateUrl: './picturi-panza.component.html',
  styleUrls: ['./picturi-panza.component.scss']
})
export class PicturiPanzaComponent implements OnInit {

  lista_picturi = pictura;

  constructor() { }

  ngOnInit(): void {
  }

}

export const pictura : Picturi[] =[
  { id: 1, name: 'Panza' },
  { id: 2, name: 'Panza' },
  { id: 3, name: 'Panza' },
  { id: 4, name: 'Panza' },
  { id: 5, name: 'Panza' },
  { id: 6, name: 'Panza' },
  { id: 7, name: 'Panza' },
  { id: 8, name: 'Panza' },
  { id: 9, name: 'Panza' },
  { id: 10, name: 'Panza' }
];
