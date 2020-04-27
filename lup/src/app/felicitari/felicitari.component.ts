import { Component, OnInit } from '@angular/core';
import { Pictura } from 'src/shared/pictura';
import { Service } from 'src/shared/service';

@Component({
  selector: 'app-felicitari',
  templateUrl: './felicitari.component.html',
  styleUrls: ['./felicitari.component.scss']
})
export class FelicitariComponent implements OnInit {

  pictura: Pictura[];
  categorie: number[];

  constructor(private service:Service) { 
    this.service.getPictura('4').subscribe(res => {
      this.pictura = res;
    },
      err => {
        console.log(err);
      })
  }

  ngOnInit(): void {
  }

}