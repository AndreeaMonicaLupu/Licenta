import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { MartisoareComponent } from './martisoare.component';

describe('MartisoareComponent', () => {
  let component: MartisoareComponent;
  let fixture: ComponentFixture<MartisoareComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ MartisoareComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(MartisoareComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
