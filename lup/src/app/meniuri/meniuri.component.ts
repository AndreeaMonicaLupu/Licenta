import { Component, OnInit } from '@angular/core';
import {Picturi} from '../picturi';

@Component({
  selector: 'app-meniuri',
  templateUrl: './meniuri.component.html',
  styleUrls: ['./meniuri.component.scss']
})
export class MeniuriComponent implements OnInit {

  lista_picturi = pictura;

  constructor() { }

  ngOnInit(): void {
  } 

}

export const pictura : Picturi[] =[
  { id: 1, name: 'Meniu' },
  { id: 2, name: 'Meniu' },
  { id: 3, name: 'Meniu' }
];
