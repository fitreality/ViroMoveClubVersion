//// fill out your copyright notice in the description page of project settings.
//
//#pragma once
//
//#include "coreminimal.h"
//#include "backendcommunication/webcommunicationbasecomponent.h"
//#include "gamestructures/spotify/spotifytypes.h"
//#include "spotifycommunicationcomponent.generated.h"
//
//declare_dynamic_multicast_delegate_oneparam(fonreadytologin, fstring, url);
//declare_dynamic_multicast_delegate(fonauthorizationsucceeded);
///**
// * 
// */
//uclass(classgroup = (custom), meta = (blueprintspawnablecomponent))
//class VIROMOVE_API uspotifycommunicationcomponent : public uwebcommunicationbasecomponent
//{
//	generated_body()
//
//public:
//
//	uproperty(blueprintassignable, category = "spotify endpoints")
//	fonreadytologin onreadytologin;
//
//	uproperty(blueprintassignable, category = "spotify endpoints")
//	fonauthorizationsucceeded onauthorizationsucceeded;
//
//	uspotifycommunicationcomponent();
//
//	//response type: getghostsformapsetresponse
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void getspotifyendpointsconfiguration(fcallbackbinding callback);
//
//	ufunction()
//	void onspotifyclienidreceived(fspotifyendpointsconfigurationresponse response);
//
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void getaccesstoken(fstring code);
//
//
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void pauseplayback(fstring accountguid);
//
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void resumeplayback(fstring accountguid);
//
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void nexttrackplayback(fstring accountguid);
//
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void previoustrackplayback(fstring accountguid);
//
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void setdevice(fsetdevicerequest request);
//
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void playtracksrequest(fplaytracksrequest request);
//
//	ufunction(blueprintcallable, category = "spotify endpoints")
//	void getdevices(fstring stationguid);
//
//private:
//	fspotifyendpointsconfigurationresponse backendresponse;
//
//	ufunction()
//	void onaccesstokenreceived(fspotifyendpointresponse response);
//
//	ufunction()
//	void onadduserauthorization();
//
//	fstring testaccountguid;
//};
