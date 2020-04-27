import { Component, OnInit } from '@angular/core';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';

@Component({
  selector: 'app-picturi-panza',
  templateUrl: './picturi-panza.component.html',
  styleUrls: ['./picturi-panza.component.scss']
})

export class PicturiPanzaComponent implements OnInit {

  pictura: Pictura[];
  categorie: number[];

   
  constructor(private service:Service) {
    this.service.getPictura('1').subscribe(res => {
      this.pictura = res;
    },
      err => {
        console.log(err);
      })

      
   }

  ngOnInit(): void {
  }

}

 