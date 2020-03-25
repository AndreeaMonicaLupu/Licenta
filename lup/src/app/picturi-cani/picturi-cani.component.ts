import { Component, OnInit } from '@angular/core';
import {Picturi} from '../picturi';


@Component({
  selector: 'app-picturi-cani',
  templateUrl: './picturi-cani.component.html',
  styleUrls: ['./picturi-cani.component.scss']
})
export class PicturiCaniComponent implements OnInit {

  lista_picturi = pictura;

  constructor() { }

  ngOnInit(): void {
  }

}

export const pictura : Picturi[] =[
  { id: 1, name: 'Cani' },
  { id: 2, name: 'Cani' },
  { id: 3, name: 'Cani' },
  { id: 4, name: 'Cani' },
  { id: 5, name: 'Cani' },
  { id: 6, name: 'Cani' },
  { id: 7, name: 'Cani' }
];
