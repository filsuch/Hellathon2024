import {Component} from '@angular/core';
import {Platform} from "@ionic/angular";
import {StatusBar, Style} from "@capacitor/status-bar";

@Component({
  selector: 'app-root',
  templateUrl: 'app.component.html',
  styleUrls: ['app.component.scss'],
})
export class AppComponent {
  private SplashScreen: any;
  constructor(private platform: Platform) {
    this.initializeApp();
  }

  initializeApp() {

  }
}
