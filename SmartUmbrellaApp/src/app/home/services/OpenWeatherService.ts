import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { Observable, from, of, throwError } from 'rxjs';
import { catchError, switchMap, map } from 'rxjs/operators';
import { Geolocation, Geoposition } from '@ionic-native/geolocation/ngx';
import { AndroidPermissions } from '@ionic-native/android-permissions/ngx';

@Injectable({
  providedIn: 'root',
})
export class OpenWeatherService {
  private readonly apiUrl: string = 'https://api.openweathermap.org/data/2.5';
  private readonly apiKey: string = '212b137b61f3b20fcc112bb7fc509ead';

  constructor(
    private http: HttpClient,
    private geolocation: Geolocation,
    private androidPermissions: AndroidPermissions
  ) {}

  // Metoda pro zajištění oprávnění pro přístup k poloze
  private checkPermissions(): Observable<boolean> {
    return from(this.androidPermissions.checkPermission(this.androidPermissions.PERMISSION.ACCESS_FINE_LOCATION)).pipe(
      switchMap((result) => {
        if (!result.hasPermission) {
          return from(
            this.androidPermissions.requestPermission(this.androidPermissions.PERMISSION.ACCESS_FINE_LOCATION)
          ).pipe(map((requestResult) => requestResult.hasPermission));
        }
        return of(true);
      }),
      catchError(() => of(false)) // Pokud dojde k chybě při žádosti o oprávnění
    );
  }

  // Získání polohy
  private getDeviceLocation(): Observable<{ lat: number; lon: number }> {
    return this.checkPermissions().pipe(
      switchMap((hasPermission) => {
        if (!hasPermission) {
          console.error('Povolení k přístupu k lokaci bylo odepřeno.');
          return of({ lat: 0, lon: 0 });
        }

        return from(this.geolocation.getCurrentPosition()).pipe(
          map((position: Geoposition) => ({
            lat: position.coords.latitude,
            lon: position.coords.longitude,
          })),
          catchError((error) => {
            console.error('Chyba při získávání polohy:', error);
            return of({ lat: 0, lon: 0 });
          })
        );
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
        return throwError({ error: 'Nepodařilo se získat počasí' });
      })
    );
  }
}
