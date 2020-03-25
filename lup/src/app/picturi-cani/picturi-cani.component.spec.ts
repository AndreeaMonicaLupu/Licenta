import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PicturiCaniComponent } from './picturi-cani.component';

describe('PicturiCaniComponent', () => {
  let component: PicturiCaniComponent;
  let fixture: ComponentFixture<PicturiCaniComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PicturiCaniComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PicturiCaniComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
