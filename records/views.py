from django.shortcuts import render

# Create your views here.
from django.http import JsonResponse
from .models import TemperatureRecord

def temperature_view(request, temp_value):
    try:
        temp_value = float(temp_value)
    except ValueError:
        return JsonResponse({'error': 'Invalid temperature value'}, status=400)

    # Create a new temperature record
    record = TemperatureRecord.objects.create(temperature=temp_value)

    return JsonResponse({
        'temperature': record.temperature,
        'time': record.timestamp.strftime("%I:%M %p"),
        'date': record.timestamp.strftime("%d/%m/%Y"),
    })

