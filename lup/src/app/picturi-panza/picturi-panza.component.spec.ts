import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PicturiPanzaComponent } from './picturi-panza.component';

describe('PicturiPanzaComponent', () => {
  let component: PicturiPanzaComponent;
  let fixture: ComponentFixture<PicturiPanzaComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PicturiPanzaComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PicturiPanzaComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
