import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { HomeComponent } from './home/home.component';
import { GalerieComponent } from './galerie/galerie.component';
import { EvenimenteComponent } from './evenimente/evenimente.component';
import { LoginComponent } from './login/login.component';


const routes: Routes = [
  {path: '', component: HomeComponent },
  {path: 'galerie', component: GalerieComponent },
  {path: 'evenimente', component: EvenimenteComponent },
  {path: 'login', component: LoginComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule { }
