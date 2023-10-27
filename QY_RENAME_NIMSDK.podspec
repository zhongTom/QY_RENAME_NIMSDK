Pod::Spec.new do |s|

    s.name     = 'QY_RENAME_NIMSDK'
    s.version  = '8.9.117.3'
    s.license  = { :"type" => "Copyright",
                   :"text" => " Copyright 2021 Netease \n"}  
    s.summary  = '网易七鱼客服访客端重命名NIMSDK'
    s.homepage = 'https://qiyukf.com'
    s.author   = { 'qiyukf' => 'yunshangfu@126.com' }
    s.source   = { :git => 'https://github.com/zhongTom/QY_RENAME_NIMSDK', :tag => "#{s.version}" }
    s.platform = :ios, '9.0'
    
    s.vendored_frameworks = '**/NIMSDK2.framework','**/h_available.framework'
    s.framework =  'SystemConfiguration', 'AVFoundation', 'CoreTelephony', 'AudioToolbox', 'CoreMedia', 'VideoToolbox'
    s.libraries = 'c++', 'z','sqlite3.0'

end

