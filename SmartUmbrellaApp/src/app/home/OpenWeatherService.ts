import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { Observable, from, of, throwError } from 'rxjs';
import { catchError, switchMap, map } from 'rxjs/operators';
import {Geolocation, Position} from '@capacitor/geolocation';


@Injectable({
  providedIn: 'root',
})
export class OpenWeatherService {
  private readonly apiUrl: string = 'https://api.openweathermap.org/data/2.5';
  private readonly apiKey: string = '212b137b61f3b20fcc112bb7fc509ead';

  constructor(private http: HttpClient) {}

  // Získání polohy
  private getDeviceLocation(): Observable<{ lat: number; lon: number }> {
    return from(Geolocation.getCurrentPosition()).pipe(
      map((position: Position) => ({
        lat: position.coords.latitude,
        lon: position.coords.longitude,
      })),
      catchError((error: any) => {
        console.error('Chyba při získávání polohy:', error);
        return of({ lat: 0, lon: 0 });  // V případě chyby vrátíme nulu
      })
    );
  }

  // Získání počasí na základě polohy
  public getWeatherByLocation(): Observable<any> {
    return this.getDeviceLocation().pipe(
      switchMap(({ lat, lon }) => {
        if (lat === 0 && lon === 0) {
          return of({ error: 'Poloha není dostupná' });
        }

        const params: HttpParams = new HttpParams()
          .set('lat', lat.toString())
          .set('lon', lon.toString())
          .set('units', 'metric')
          .set('lang', 'cz')
          .set('appid', this.apiKey);

        return this.http.get(`${this.apiUrl}/weather`, { params });
      }),
      catchError((error: any): Observable<{ error: string }> => {
        console.error('Chyba při získávání počasí:', error);
        return of({ error: 'Nepodařilo se získat počasí' });
      })
    );
  }
}
