import { Component, OnInit } from '@angular/core';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';

@Component({
  selector: 'app-meniuri',
  templateUrl: './meniuri.component.html',
  styleUrls: ['./meniuri.component.scss']
})
export class MeniuriComponent implements OnInit {

  pictura: Pictura[];
  categorie: number[];

  
  constructor(private service:Service) {
    this.service.getPictura('6').subscribe(res => {
      this.pictura = res;
    },
      err => {
        console.log(err);
      })

   }

  ngOnInit(): void {
  } 

}
