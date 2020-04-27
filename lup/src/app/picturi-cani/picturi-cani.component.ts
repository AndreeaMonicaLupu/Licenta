import { Component, OnInit } from '@angular/core';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';


@Component({
  selector: 'app-picturi-cani',
  templateUrl: './picturi-cani.component.html',
  styleUrls: ['./picturi-cani.component.scss']
})
export class PicturiCaniComponent implements OnInit {

  pictura: Pictura[];
  categorie: number[];

  constructor(private service:Service) { 
    this.service.getPictura('3').subscribe(res => {
      this.pictura = res;
    },
      err => {
        console.log(err);
      })
  }

  ngOnInit(): void {
  }

}
