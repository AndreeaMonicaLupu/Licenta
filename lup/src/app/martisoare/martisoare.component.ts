import { Component, OnInit } from '@angular/core';
import {Picturi} from '../picturi';

@Component({
  selector: 'app-martisoare',
  templateUrl: './martisoare.component.html',
  styleUrls: ['./martisoare.component.scss']
})
export class MartisoareComponent implements OnInit {  

  lista_picturi = pictura;

  constructor() { }

  ngOnInit(): void {
  }

}

export const pictura : Picturi[] =[
  { id: 1, name: 'Martisor' },
  { id: 2, name: 'Martisor' }
];
