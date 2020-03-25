import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';

import {MatButtonModule} from '@angular/material/button';
import {MatMenuModule} from '@angular/material/menu';
import {MatGridListModule} from '@angular/material/grid-list';
import {MatInputModule} from '@angular/material/input';
import {MatCardModule} from '@angular/material/card'
import {MatExpansionModule} from '@angular/material/expansion'

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HomeComponent } from './home/home.component';
import { GalerieComponent } from './galerie/galerie.component';
import { EvenimenteComponent } from './evenimente/evenimente.component';
import { LoginComponent } from './login/login.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { PicturiPanzaComponent } from './picturi-panza/picturi-panza.component';
import { PicturiPereteComponent } from './picturi-perete/picturi-perete.component';
import { PicturiCaniComponent } from './picturi-cani/picturi-cani.component';
import { FelicitariComponent } from './felicitari/felicitari.component';
import { MartisoareComponent } from './martisoare/martisoare.component';
import { MeniuriComponent } from './meniuri/meniuri.component';

@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    GalerieComponent,
    EvenimenteComponent,
    LoginComponent,
    PicturiPanzaComponent,
    PicturiPereteComponent,
    PicturiCaniComponent,
    FelicitariComponent,
    MartisoareComponent,
    MeniuriComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    BrowserAnimationsModule,
    FormsModule,
    MatButtonModule,
    MatMenuModule,
    MatGridListModule,
    MatInputModule,
    MatCardModule,
    MatExpansionModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
