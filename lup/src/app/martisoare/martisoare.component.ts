import { Component, OnInit } from '@angular/core';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';

@Component({
  selector: 'app-martisoare',
  templateUrl: './martisoare.component.html',
  styleUrls: ['./martisoare.component.scss']
})
export class MartisoareComponent implements OnInit {  

  pictura: Pictura[];
  categorie: number[];
  
  constructor(private service:Service) { 
    this.service.getPictura('5').subscribe(res => {
      this.pictura = res;
    },
      err => {
        console.log(err);
      })
  }

  ngOnInit(): void {
  }

}