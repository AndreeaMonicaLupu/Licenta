import { Component, OnInit } from '@angular/core';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';

@Component({
  selector: 'app-picturi-perete',
  templateUrl: './picturi-perete.component.html',
  styleUrls: ['./picturi-perete.component.scss']
})

export class PicturiPereteComponent implements OnInit {
  
  pictura: Pictura[];
  categorie: number[];

  constructor(private service:Service) {
    this.service.getPictura('2').subscribe(res => {
      this.pictura = res;
    },
      err => {
        console.log(err);
      })
   }

  ngOnInit(): void {
  }

}
