import { Component, OnInit } from '@angular/core';
import {  Router } from '@angular/router';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})
export class HomeComponent implements OnInit {

  constructor(private router: Router) {}

  ngOnInit(): void {
  }
  
  cale: string;
  
  Redirect_Evenimente(cale){
    this.cale=cale;

    this.router.navigate([cale]);

    window.scrollTo(0, 0);

}
}
