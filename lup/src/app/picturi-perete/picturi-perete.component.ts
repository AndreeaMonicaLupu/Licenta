import { Component, OnInit } from '@angular/core';
import {Picturi} from '../picturi'

@Component({
  selector: 'app-picturi-perete',
  templateUrl: './picturi-perete.component.html',
  styleUrls: ['./picturi-perete.component.scss']
})

export class PicturiPereteComponent implements OnInit {

  lista_picturi = pictura;

  constructor() { }

  ngOnInit(): void {
  }

}

export const pictura : Picturi[] =[
  { id: 1, name: 'Perete' },
  { id: 2, name: 'Perete' },
  { id: 3, name: 'Perete' },
  { id: 4, name: 'Perete' },
  { id: 5, name: 'Perete' }
];
