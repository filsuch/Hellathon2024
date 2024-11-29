import { Component } from '@angular/core';
import {OpenWeatherService} from "./services/OpenWeatherService";



@Component({
    selector: 'app-home',
    templateUrl: 'home.page.html',
    styleUrls: ['home.page.scss'],
    standalone: false
})
export class HomePage {
  public weather_data: any = null;
  public error_message: string | null = null;

  constructor(private weather_service: OpenWeatherService) {}



  public get_weather(): void {
    this.weather_service.getWeatherByLocation()
      .subscribe({
        next: (data: any): void => {
          this.weather_data = data;
          this.error_message = null;
        },
        error: (error: any): void => {
          this.error_message = 'Nepodařilo se načíst počasí';
          console.error('Chyba:', error);
        }
      });
  }

}
