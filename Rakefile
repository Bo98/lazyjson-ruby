require "rake/extensiontask"
require "json"
require "net/http"
require "tempfile"

Rake::ExtensionTask.new("lazyjson")

desc "Update vendored simdjson"
task :simdjson do
  def fetch(url, filename)
    Net::HTTP.get_response(url) do |response|
      case response
      when Net::HTTPSuccess
        tmpfile = Tempfile.new(filename)
        begin
          md5 = Digest::MD5.new
          response.read_body do |chunk|
            md5 << chunk
            tmpfile.write chunk
          end
          tmpfile.close
          raise "Checksum mismatch" if md5.base64digest != response["content-md5"]
          File.rename(tmpfile.path.to_s, File.join(__dir__, "ext", "lazyjson", filename))
        ensure
          tmpfile.close!
        end
      when Net::HTTPRedirection
        fetch(URI(response["location"]), filename)
      else
        response.error!
      end
    end
  end

  asset_data = JSON.parse(Net::HTTP.get(URI("https://api.github.com/repos/simdjson/simdjson/releases/latest")))["assets"]

  ["simdjson.h", "simdjson.cpp"].each do |filename|
    download_url = URI(asset_data.find { |asset| asset["name"] == filename }["browser_download_url"])
    fetch(download_url, filename)
  end
end

desc "Launch IRB session"
task :irb do
  require "lazyjson"
  require "irb"
  ARGV.clear
  IRB.start
end
