import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { FelicitariComponent } from './felicitari.component';

describe('FelicitariComponent', () => {
  let component: FelicitariComponent;
  let fixture: ComponentFixture<FelicitariComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ FelicitariComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(FelicitariComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
