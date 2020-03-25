import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { MeniuriComponent } from './meniuri.component';

describe('MeniuriComponent', () => {
  let component: MeniuriComponent;
  let fixture: ComponentFixture<MeniuriComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ MeniuriComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(MeniuriComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
