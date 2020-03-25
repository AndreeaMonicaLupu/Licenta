import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PicturiPereteComponent } from './picturi-perete.component';

describe('PicturiPereteComponent', () => {
  let component: PicturiPereteComponent;
  let fixture: ComponentFixture<PicturiPereteComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PicturiPereteComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PicturiPereteComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
